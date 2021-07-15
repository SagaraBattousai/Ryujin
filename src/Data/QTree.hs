module Data.QTree where

type Point = (Int, Int)
type Points = [Point]

-- AABB = Axis Aligned Bounding Box
-- data AABB = AABB { center :: Point, halfHeight :: Float, halfWidth :: Float }
data AABB = AABB { topLeft :: Point
                 , bottomRight :: Point
                 } deriving (Show)

data QTree = Empty | Node AABB Points QTree QTree QTree QTree

center :: AABB -> Point
center x = (xc, yc)
  where
    tl = topLeft x
    br = bottomRight x
    xc = (flip div 2) $ (fst tl) + (fst br)
    yc = (flip div 2) $ (snd tl) + (snd br)

{-               (xc, y1)     
 - (x1,y1)  *--------*--------* (x2, y1)
 -          |        |        |
 -          |        |        |
 -          |    (xc, yc)     |
 - (x1, yc) *________*________* (x2, yc)
 -          |        |        |
 -          |        |        |
 -          |        |        |
 - (x1, y2) *--------*--------* (x2, y2)
 -               (xc, y2)
 -}

q1 :: AABB -> AABB
q1 bb = AABB (topLeft bb) (center bb)

q2 :: AABB -> AABB
q2 bb = AABB (xc, y1) (x2, yc)
  where
    (xc, yc) = center bb
    (x2, y1) = (fst $ bottomRight bb, snd $ topLeft bb)

q3 :: AABB -> AABB
q3 bb = AABB (x1, yc) (xc, y2)
  where
    (xc, yc) = center bb
    (x1, y2) = (fst $ topLeft bb, snd $ bottomRight bb)

q4 :: AABB -> AABB
q4 bb = AABB (center bb) (bottomRight bb)

singleton :: Point -> QTree
singleton x = Node bb [x] Empty Empty Empty Empty
  where
    (x2, y2) = (fst x + 1, snd x + 1)
    bb = AABB x (x2, y2)

--insert :: AABB -> QTree AABB -> Qtree AABB
--insert x Empty = singleton x
--insert bb (Node root ne se sw nw)
--  |
--  where
--    q1 = root

