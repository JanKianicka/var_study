; Scheme lessons written by Trigvi - very nice book full of joges.
; Load file to DFX scheme interpreter by:
; (load '/home/local/kianicka/repositories/prj_2013_ctbto_autoshi_testing/kianicka/scheme/Scheme_lessons.scm)

(define (foo x y) ( + (* a x x) (* b y y) c))

(define a 0)
(define b 3)
(define c 11)

; lambda is creating nameless function
; example from IDC code
(define (find-alpha-list-arrivals origin)
  (mapcan (lambda (x)
	    (if (on-list? x *alpha-list-arrivals*)
		(list x)))
	  (find-origin-associated-arrivals origin)))
; These two are the same
(define double_num (lambda (n) (+ n n)))
(define (double_num n) (+ n n))
(print "Result of double_num") 
(print (double_num 6)) 


; List is an empty list or an element on the front end of the list.
; (a b c) - each is 'conses'
; car returns head
; cdr returns the tail

(define simplelist '(abe male spiritus))
(car (cdr (cdr simplelist)))

; caddr returns twice cdr
(caddr simplelist)

; Exercise on lists
(define argex '(foo (bar bel) (sic transit gloria) redhat))

; Third element
(define (third x) (caddr x))
;returning of 'gloria'
(third (third argex))

; Buliding of list
(set! my_list (list (third '(abi abu abe))
(car '(male female))
(cadr '(sanctus spiritus)) ) )
; quote - '(abi male spiritus) says
; this is the list without being evaluated
; (quote (abi male spiritues)

; adding element to (the front of) the list:
; function cons

(define sta 'a)
(set! *array-names* (cons 'abe '(male spiritus)))
(set! *array-names* (cons sta *array-names*))

; Addind together two lists.
(define treaties '(test-ban free-trade nonprolif))
(define orgs '(un ctbto iaea fpa unesco))
(append orgs treaties)
(append treaties orgs)

; append! modifies original list - changed dead-end of the list

; Chaning of elements
(define lyst '(nuclear proliferation treaty))
(set-car! lyst 'chemical)
; lyst is now: (chemical proliferation treaty)
; there is also set-cdr! 

; Verification of implemented if sequence
(define (check_if x)
  (if (null? x)
      (print "Error of database query %s" (list x))
      (if (eq? x 'container)
	  (print "Info: No objects found for query %s" (list x))
	  x)))

; The verification was correct
; (define yy 'container)
; (set! xx (check_if yy))
; "Info: No objects found for query %s"
; ()
; xx is now empty
; (define gg 'something_else)
; (set! xx (check_if gg))
; xx is now 'something_else
; This confirmed that our implemention of getting container is
; correct.


; General conditional 
(define a 'smile)

(cond ((eq? a 'smille) (print "Hello true!"))
((eq? a 'smile) (print "Hello false!")))

; False testing
(define false ())
; > false
; ()

(if false (print "Nothing"))

; Ex7: Manipulate the list
(define (replace before after)
  (set-car! before (car after))
  (set-cdr! before (cdr after))
  after)

; it seems I do not understand it much
; > (replace (cddr lyst) '(three four five))
; (three four five)
; > lyst
; (one two three four five)

; Eq8: checking member ship and using recursion

(define (member? item lyst)
  (cond ((null? lyst) '())
	((eqv? item (car lyst)) t)
	(t (member? item (cdr lyst)))))

; result
;> (member? 'abe '(homer marge abe bart lisa maggie))
;t
;> (member? 'abe '(homer marge abee bart lisa maggie))
;()

; Arithemtic operand does not work as expected
; (+ 1 1 1)
; returns 2, always considers only forst two operands

;begin for is the list of expressions like in normal programming

;let and lat* forms do <binding> <body>

(define (set_up)
  (let* ((first cons('aby))
	 (set! first (cons '('first 'firts)))
	 (value2 (+ 2 2))
	 (value3 (+ 3 value2))
    ))
  ;this does not print anything - only global variable which has been not changed
  ; and print does not work in this case
  (print (string-format "Value of local value3: %d"(list value3)))
  )

; One more excercise with let* form.
; two parts - let* (<bindings>)(<body>)
(set! a 3)
(set! b 4)
(let* ((a(set! a 4))
       )
      (print a)
      (if(equal a 3)(set! a 1))
      (print b))
; should produce:
; 4.000000
; 3.000000
; ()
;Try these two:
; (let* ((a(set! a 4)))(print a)(if(equal a 4)(print "Hello"))(print b))
; (let* ((a(set! a 4)))(print a)(if(equal a 3)(print "Hello"))(print b))
;


(define (set_up2)
  (let* ((value2 (+ 2 2))
	 (value3 (+ 3 value2))
    )) value3)

; I did not found how this works ... it should return value3 but return just false ().
; Now when I have put it outside from bracket it is returned, but why it did
; not print in previous implementation - horrible language!!!
; Java and python are somewhere quite else!

; do loop
(define (factorial n)
  (do ((i n (- i 1))
       (a 1 (* a i))
      ((zero? i) a))
   )
)
;(set! fact_res (factorial 10))
;(print fact_res) -- this example from the book does not work
;(define iter 5) 
;(do (
;     (iter (- itern 1))
;     (print iter)
;     (zero? iter)
;    )
;) -- looks like 'do' is not implemented in IDC scheme interpreter

(set! ll1 '(one two three))
(set! ll2 '(ein zwei drei))
(map (lambda (a) (list a))
     ll1)
;(map (lambda (a b) (list a b))
;     ll1 ll2) -- this did not work for me in IDC scheme, looks like
; lambda is capable to have just one input argument
; ((lambda (a b) (list a b)) ll1 ll1) -- this works, so really there can be two arguments for lambda
(define (join_lists a b) (list a b))
(join_lists ll1 ll2) ;--this works
; (map join_lists (ll1 ll2)) -- does not work
; (map join_lists ll1 ll2) -- does not work

; this example works
(define eng-fre '((one un) (two deux) (three trois)))
(map cadr eng-fre)
; returns (un deux trois)
(map car eng-fre)
;returns (one two three)
; <proc> is used on ech element of the the input list
(define (print_value a)(print a))
(map print_value '("a" "b" "c")) ; --- great, this works

; test behavior of function defined within function
; I can extract function test_in as global one in this file
(define (test_in x) (begin 
		      (+ x 1)
		      (print "Call of test_in function.")
		      ))

(define (process-origin-for-initsite)
;  (define (test_in x) (begin 
;			 (+ x 1)
;			 (print "Call of test_in function.")
;			 ))
; yes, this works - therefore I can refactor function process-origin-for-initsite like this 
; and make it shorter
  (test_in 2)
  )
(process-origin-for-initsite)
;(test_in 2) -- this is impossible because test_in is local to process-origin-for-initsite

