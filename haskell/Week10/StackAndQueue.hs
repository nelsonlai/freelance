{-|
Module      : StackAndQueue
Author      : COMP1100 Team, Your name and UID here
Date        : 
Description : Exercises with stacks and queues 
-}

module StackAndQueue where

-- Definitions for stacks

type Stack = []

push :: a -> Stack a -> Stack a
push = (:)

pop :: Stack a -> (a,Stack a)
pop stack = case stack of
  []   -> error "pop on empty stack"
  x:xs -> (x,xs)

{-
Exercise 1: Use a Maybe type to write a 'safe' version of pop.
-}

safePop :: Stack a -> (Maybe a,Stack a)
safePop stack = case stack of
  []   -> (Nothing, [])
  x:xs -> (Just x, xs)

-- Definitions for queues

class Queue q where
  enqueue  :: a -> q a -> q a
  dequeue  :: q a -> (a,q a)
  emptyQ   :: q a
  isEmptyQ :: q a -> Bool

{-
Exercise 2: Define a list as an Instance of the Queue typeclass,
with fast enqueue and slow dequeue.
emptyQ and isEmptyQ are written for you.
-}

instance Queue [] where

  enqueue x list = list ++ [x]

  dequeue list = case list of
    [] -> error "dequeue on empty queue"
    x:xs -> (x, xs)

  emptyQ = []

  isEmptyQ = null

{-
Exercise 3: write a function that dequeues every item from a
Queue, inserting them into a Stack as you go.
-}

queueToStack :: Queue q => q a -> Stack a
queueToStack queue
    | isEmptyQ queue = []
    | otherwise = let (x, remaining) = dequeue queue
                  in x : queueToStack remaining

-- `Two list' implementation of a queue. Provided for your testing
-- and does not need to be edited.

data TwoListQueue a = Queue [a] [a]
  deriving Show

instance Queue TwoListQueue where

  enqueue x (Queue output input) = Queue output (x:input)

  dequeue (Queue output input) = case (output,input) of
    ([],[])  -> error "dequeue on empty queue"
    (x:xs,_) -> (x,Queue xs input)
    ([],_)   -> dequeue (Queue (reverse input) [])

  emptyQ = Queue [] []

  isEmptyQ (Queue output input) = null output && null input

