;;; Converting uncompressed BMP file to C array with BW pixels for EPD. 

(defstruct rgb
  (r 0 :type (unsigned-byte 8))
  (g 0 :type (unsigned-byte 8))
  (b 0 :type (unsigned-byte 8)))

(defun read-rgb (f)
  (make-rgb :r (read-byte f) :g (read-byte f) :b (read-byte f)))

(defstruct bmp
  (w 0 :type fixnum)
  (h 0 :type fixnum)
  pixels)

(defun little (seq &optional (sum 0) (scale 1))
  (if (equal (length seq) 0)
      sum
      (little (subseq seq 1) (+ sum (* scale (aref seq 0))) (* scale 256))))

(defun read-bmp-header (f)
  (let ((a (make-array 54 :element-type '(unsigned-byte 8))))
    (read-sequence a f)
    (assert (and (equalp (subseq a 0 2) #(66 77))))
    (assert (equalp (subseq a 6 10) #(0 0 0 0)))
    (assert (equal (little (subseq a 10 14)) 54))
    (assert (equal (little (subseq a 14 18)) 40))
    (values (little (subseq a 18 22))
	    (little (subseq a 22 26)))))

(defun read-bmp-pixels (f w h)
  (let ((a (make-array (* w h) :element-type 'rgb :initial-element (make-rgb))))
    (loop for y from (1- h) downto 0 do
      (loop for x from 0 to (1- w) do
	(setf (aref a (+ x (* y w))) (read-rgb f))))
    a))

(defun read-bmp (f)
  (multiple-value-bind (w h) (read-bmp-header f)
    (make-bmp
     :w w
     :h h
     :pixels (read-bmp-pixels f w h))))

(defun bw (seq)
  (map 'vector
       (lambda (p)
	 (if (< (+ (rgb-r p) (rgb-g p) (rgb-b p)) 700) 1 0))
       seq))

(defun tobyte (seq &optional (out 0))
  (if (equal (length seq) 0)
      out
      (tobyte (subseq seq 1) (+ (aref seq 0) (* 2 out)))))

(defun comprez (a)
  (let ((b (make-array (/ (length a) 8))))
    (dotimes (i (length b) b)
      (setf (aref b i) (tobyte (subseq a (* 8 i) (* 8 (1+ i))))))))

(defun write-sequence-content (f seq)
  (when (> (length seq) 0)
    (if (> (length seq) 22)
	(progn
	  (format f "~%   ~{ 0x~2,'0x,~}" (coerce (subseq seq 0 22) 'list))
	  (write-sequence-content f (subseq seq 22)))	
	(format f "~%   ~{ 0x~2,'0x~^,~}};~%" (coerce seq 'list)))))

(defun convert (fname varname)
  (with-open-file (f fname :element-type '(unsigned-byte 8))
    (let* ((bmp (read-bmp f))
	   (w (bmp-w bmp))
	   (h (bmp-h bmp)))
      (with-open-file (g (concatenate 'string fname ".h")
			 :direction :output
			 :if-does-not-exist :create
			 :if-exists :supersede)
	(format g "extern const unsigned char ~a_~ax~a[];~%" varname w h))
      (with-open-file (g (concatenate 'string fname ".c")
			 :direction :output
			 :if-does-not-exist :create
			 :if-exists :supersede)
	(format g "#include ~s~%~%" (concatenate 'string fname ".h"))
	(format g "const unsigned char ~a_~ax~a[] = {" varname w h)
	(write-sequence-content g (comprez (bw (bmp-pixels bmp))))))))
