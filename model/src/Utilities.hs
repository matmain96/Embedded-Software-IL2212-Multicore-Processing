-----------------------------------------------------------------------------
-- |
-- Module      :  Utilities
-- Copyright   :  (c) George Ungureanu, 2019
-- License     :  BSD3
-- Maintainer  :  ugeorge@kth.se
--
-- This module contains utility functions.
-----------------------------------------------------------------------------
module Utilities (
  -- * Image utilities

  -- | Collection of functions for reading, printing or converting
  -- between image formats.
  readPPM, readAllPPM, ppm2matrix, toAsciiArt, toAsciiArt', printAscii, printAscii',

  -- * List utilities
  splitEvery
  ) where

import Data.List (intercalate, isPrefixOf)
import Data.Maybe (isNothing)
import Text.Read
import ForSyDe.Shallow.Core.Vector
import ForSyDe.Shallow.Utility.Matrix

-- | Reads the contents of a
-- <https://en.wikipedia.org/wiki/Netpbm_format P3 PPM file> and
-- returns a list with the pixel values, along with the dimensions of
-- the image.
readPPM :: String            -- ^ file content
        -> (Int, Int, [Int]) -- ^ (X dimension, Y dimension, list of pixel values)
readPPM str = (dimX, dimY, image)
  where
    imageData = map read $ dropWhile (\a -> isNothing (readMaybe a :: Maybe Int)) $ words str :: [Int]
    --imageData = map (fst . fromJust . C8.readInt) $ tail $ C8.words str :: [Int]
    (dimX, dimY, _, image)  = getHeader imageData
    getHeader (x:y:max:img) = (x, y, max, img)
    
-- | IO function which takes a list of paths to P3 PPM images, reads
-- the files with 'readPPM', checks if all images have the same
-- dimensions, concatenates all images and returns the obtained list
-- of pixel values along with the picture dimensions.
readAllPPM :: [FilePath]           -- ^ list of paths to PPM images
           -> IO (Int, Int, [Int])
           -- ^ IO (X dimension, Y dimension, list of pixel values from all images)
readAllPPM paths = do
  imageFiles <- mapM readFile paths
  let (xs,ys,images) = unzip3 $ map readPPM imageFiles
      xdim = head xs
      ydim = head ys
      imageSigs
        | not (all (==xdim) xs) = error "not all images have the same X dimension"
        | not (all (==ydim) ys) = error "not all images have the same Y dimension"
        | otherwise = foldl1 (++) images
  return (xdim, ydim, imageSigs)

-- | Reads the contents of a
-- <https://en.wikipedia.org/wiki/Netpbm_format P3 PPM file> and
-- returns a ready image. Useful for testing the image processing
-- functions from the "Tracker" module.
ppm2matrix str = let (x, y, ppm) = readPPM str
                 in  matrix (x * 3) y ppm

-- | List with grayscale levels encoded as ASCII characters
asciiLevels :: [Char]
asciiLevels = [' ','.',':','-','=','+','/','t','z','U','w','*','0','#','%','@']

-- | Converts an image of values to an equivalent 16-valued
-- representation in ASCII art.
toAsciiArt :: (Num a, Dividable a)
           => a           -- ^ the maximum value that is equivalent to the highest possible pixel luminosity
           -> Matrix a    -- ^ input image of pixel values
           -> Matrix Char -- ^ output image of ASCII characters
toAsciiArt vMax = mapMat num2char
  where
    num2char n = asciiLevels !! level n
    level n = toInt $ (fromIntegral nLevels) * (n // vMax)
    nLevels = length asciiLevels - 1

-- | The same as 'toAsciiArt' but identifies the maximum value from the image.
toAsciiArt' :: (Ord a, Num a, Dividable a)
            => Matrix a    -- ^ input image of pixel values
            -> Matrix Char -- ^ output image of ASCII characters
toAsciiArt' img = toAsciiArt (reduceMat max img) img

-- | IO function that conveniently pretty-prints a matrix of values
-- into an ASCII-art image. See 'toAsciiArt'.
printAscii vMax = mapM_ putStrLn . map fromVector . fromVector . toAsciiArt vMax

-- | IO function that conveniently pretty-prints a matrix of values
-- into an ASCII-art image. See 'toAsciiArt''.
printAscii' :: (Ord a, Num a, Dividable a) => Matrix a -> IO ()
printAscii' = mapM_ putStrLn . map fromVector . fromVector . toAsciiArt'

-- | Function used for convenience, to avoid loading external
-- packages. Splits a list into a list of lists of length @n@.
splitEvery :: Int -> [a] -> [[a]]
splitEvery _ [] = []
splitEvery n l = take n l : splitEvery n (drop n l)


-----------------------------------------------------------------------------
-- Below is a custom hack to fit both Integral and Real as inputs for
-- 'toAsciiArt' function. Since the type semantics of 'Dividable' is
-- not correct in the general case, this class in not exported.
-----------------------------------------------------------------------------

class Num a => Dividable a where
  (//) :: a -> a -> a
  toInt :: a -> Int

instance Dividable Integer where
  (//)  = div
  toInt = fromIntegral

instance Dividable Int where
  (//)  = div
  toInt = id

instance Dividable Float where
  (//)  = (/)
  toInt = truncate

instance Dividable Double where
  (//) = (/)
  toInt = truncate
