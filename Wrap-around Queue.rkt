;; wrap-around queue
#lang racket
(define-struct queue (vec start end) #:mutable)
(define (new-queue n) ;; returns a queue that can store n elements
  (make-queue (make-vector (+ 1 n)) 0 0))
(define (empty-queue? q)
  (= (queue-start q) (queue-end q)))
(define (enqueue q val)
  (cond
    [(= (add1 (queue-start q)) (queue-end q)) error "full"]
    [(= (add1 (queue-start q)) (vector-length (queue-vec q)))
     (vector-set! (queue-vec q) 0 val)
     (set-queue-start! q 0)]
    [true
     (vector-set! (queue-vec q) (queue-start q) val)
     (set-queue-start! q (add1 (queue-start q)))]))
(define (dequeue q)
  (cond
    [(empty-queue? q) error "empty"]
    [(= (add1 (queue-end q)) (vector-length (queue-vec q)))
     (begin
       (define res (vector-ref (queue-vec q) (queue-end q)))
       (set-queue-end! q 0)
       res)]
    [true (begin
            (define res (vector-ref (queue-vec q) (queue-end q)))
            (set-queue-end! q (+ (queue-end q) 1))
            res)]))
     