#lang racket
; from TA hint code and TA slide + my implementation
(define (lambda? x)
  (member x '(lambda λ)))
(define LAMBDA (string->symbol "\u03BB"))
(define (expr-compare x y)
  (cond [(equal? x y) x]
        [(and (boolean? x) (boolean? y))  (if x '% '(not %))]
        [(and (list? y) (list? x) (= (length y) (length x))) 
          (cond [(unique (first y) (first x)) (list 'if '% x y)]
                [(and (lambda? (first y)) (lambda? (first x))) (lambda-list x y '() '())]
                [else (recursive-compare x y)]
          )]
        [else (list 'if '% x y)]
  )
)

; my implementation
(define (recursive-compare x y)
  (cond [(empty? x) x]
        [(not (equal? (first y) (first x))) (cons (expr-compare (first x) (first y)) (recursive-compare (rest x) (rest y)))]
        [else (cons (first x) (recursive-compare (rest x) (rest y)))]
  )
)

(define (unique x_prim y_prim)
  (or (xor (lambda? x_prim) (lambda? y_prim))
      (or (equal? x_prim 'quote) (equal? y_prim 'quote)) ;can be double quote
      (xor (equal? x_prim 'if) (equal? y_prim 'if))
  )
)

; everything below is for THE lambda
(define (lambda-list x y dictionaryx dictionaryy)
  (cond [(not (= (length (cadr y)) (length (cadr x)))) (list 'if '% x y)]
        [(and (equal? (first y) 'lambda) (equal? (first x) 'lambda)) (list 'lambda (arguments (cadr x) (cadr y)) (lambda-body (cons (dictionary (cadr x) (cadr y)) dictionaryx) (cons (dictionary2 (cadr x) (cadr y)) dictionaryy) (caddr x) (caddr y)))]
        [else (list LAMBDA (arguments (cadr x) (cadr y)) (lambda-body (cons (dictionary (cadr x) (cadr y)) dictionaryx) (cons (dictionary2 (cadr x) (cadr y)) dictionaryy) (caddr x) (caddr y)))]
  )
)

(define (lambda-body dictionaryx dictionaryy xbody ybody )
  (cond [(and (equal? (search xbody dictionaryx ) "DNE") (equal? (search ybody dictionaryy) "DNE") (equal? xbody ybody)) xbody]
        [(equal? (if (not (equal? (search xbody dictionaryx) "DNE")) (search xbody dictionaryx ) xbody) (if (not (equal? (search ybody dictionaryy ) "DNE")) (search ybody dictionaryy) ybody)) (if (not (equal? (search xbody dictionaryx) "DNE")) (search xbody dictionaryx ) xbody)]
        [(and (not (list? xbody)) (list? ybody)) (expr-compare xbody (mapping ybody dictionaryy ))]        
        [(and (list? xbody) (not (list? ybody))) (expr-compare (mapping xbody dictionaryx) (if (not (equal? (search ybody dictionaryy ) "DNE")) (search ybody dictionaryy) ybody))]
        [(and (not (list? xbody)) (not (list? ybody))) (expr-compare (if (not (equal? (search xbody dictionaryx) "DNE")) (search xbody dictionaryx ) xbody) (if (not (equal? (search ybody dictionaryy ) "DNE")) (search ybody dictionaryy) ybody))]
        [else (expr-compare (mapping xbody dictionaryx) (mapping ybody dictionaryy))]
  )
)

(define (arguments argx argy)
  (cond [(empty? argx) argx]
        [(equal? (first argy) (first argx)) (cons (first argx) (arguments (rest argx) (rest argy)))]
        [else (cons (combine-terms (first argx) (first argy)) (arguments (rest argx) (rest argy)))]
  )
) 

(define (dictionary x y)
  (cond [(empty? x) (hash)]
        [(equal? (first y) (first x)) (dictionary (rest x) (rest y))]
        [else (hash-set (dictionary (rest x) (rest y)) (first x) (combine-terms (first x) (first y)))]        
  )
)

(define (dictionary2 x y)
  (cond [(empty? x) (hash)]
        [(equal? (first y) (first x)) (dictionary2 (rest x) (rest y))]
        [else (hash-set (dictionary2 (rest x) (rest y)) (first y) (combine-terms (first x) (first y)))]        
  )
)

(define (combine-terms x y)
  (string->symbol (string-append (symbol->string x) "!" (symbol->string y)))
)

(define (mapping x dict-list)
  (cond [(empty? x) x]
        [(boolean? (first x)) (cons (first x) (mapping2 (rest x) dict-list))]
        [(lambda? (first x)) (cons (first x) (cons (cadr x) (mapping (cddr x) (cons (self-dictionary (cadr x)) dict-list))))]
        [(equal? (first x) 'quote) x]
        [(equal? (first x) 'if) (cons (first x) (mapping2 (rest x) dict-list))]
        [(list? (first x)) (cons (mapping (first x) dict-list) (mapping2 (rest x) dict-list))]
        [else (cons (if (not (equal? (search (first x) dict-list) "DNE")) (search (first x) dict-list) (first x) ) (mapping2 (rest x) dict-list))]
  )
)

(define (mapping2 x dict-list)
  (cond [(empty? x) x]
        [(boolean? (first x)) (cons (first x) (mapping2 (rest x) dict-list))]
        [(list? (first x)) (cons (mapping (first x) dict-list) (mapping2 (rest x) dict-list))]
        [else (cons (if (not (equal? (search (first x) dict-list) "DNE")) (search (first x) dict-list) (first x) ) (mapping2 (rest x) dict-list))]
  )
)

(define (self-dictionary input)
  (cond [(empty? input) (hash)]
        [else (hash-set (self-dictionary (rest input)) (first input) (first input))]
 )
)

(define (search element dict-list )
  (cond [(empty? dict-list) "DNE"]
        [(not (equal? (hash-ref (first dict-list) element "DNE_in_dict") "DNE_in_dict")) (hash-ref (first dict-list) element)]
        [else (search element (rest dict-list) )]
  )
)
  


(define ns (make-base-namespace))
; from TA hint code  
(define (test-expr-compare x y) 
  (and (equal? (eval x)
               (eval `(let ((% #t)) ,(expr-compare x y))))
       (equal? (eval y)
               (eval `(let ((% #f)) ,(expr-compare x y))))))

(define test-expr-x
  '(lambda (a b) (lambda (a c) (if #f '(c b) (lambda (e) (e)))))
)

(define test-expr-y
  '(λ (b a) (lambda (a d) (if #t (quote (a d)) (lambda (d e) (+ d e c)))))
)
