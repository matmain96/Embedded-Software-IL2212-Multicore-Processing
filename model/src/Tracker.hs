-----------------------------------------------------------------------------
-- |
-- Module      :  Tracker
-- Copyright   :  (c) George Ungureanu, 2019
-- License     :  BSD3
-- Maintainer  :  ugeorge@kth.se
--
-- Contains the image processing functions as well as the DUT process
-- network instantiation.
-----------------------------------------------------------------------------
module Tracker where

import ForSyDe.Shallow
import Utilities

dSPAN = 15 :: Int

cropSIZE = 2 * dSPAN + 1 :: Int

xPATTERN = matrix 5 5 [
  0,0,1,0,0,
  0,1,0,1,0,
  1,0,0,0,1,
  0,1,0,1,0,
  0,0,1,0,0
  ] :: Matrix Double

------------------------------------------------------------
--              Image processing functions                --
------------------------------------------------------------

grayscale :: Matrix Int -> Matrix Double
grayscale = mapMat (convert . fromVector) . mapV (groupV 3)
  where
    convert [r,g,b] = fromIntegral r * 0.3125
                    + fromIntegral g * 0.5625
                    + fromIntegral b * 0.125
    convert _ = error "RGB image length is not a multiple of 3"

crop :: [Int] -> Matrix Double -> Matrix Double
crop [cX,cY] img = cropMat cropSIZE cropSIZE cX cY img

xcorr2 :: Matrix Double -> Matrix Double -> Matrix Double
xcorr2 pat img = mapMat (reduceMat (+)) products
  where
    products    = mapMat timesP stencils
    timesP mat  = zipWithMat (*) pat mat
    stencils    = stencilMat patW patH img
    (patW,patH) = sizeMat pat

posMax :: Matrix Double -> [Int]
posMax img = [cX, cY]
  where
    ((cX,cY),_) = reduceMat findMax $ zipMat indexMat img
    findMax (c1,v1) (c2,v2) | v1 >= v2  = (c1,v1)
                            | otherwise = (c2,v2)

calcCoord :: [Int] -> Matrix Double -> [Int]
calcCoord [prevX,prevY] img = [cropX,cropY]
  where
    cropX | prevX <= dSPAN     = 0
          | prevX > imgW-dSPAN = imgW - cropSIZE - 1
          | otherwise          = prevX - dSPAN - 1
    cropY | prevY <= dSPAN     = 0
          | prevY > imgH-dSPAN = imgH - cropSIZE - 1
          | otherwise          = prevY - dSPAN - 1
    (imgW,imgH) = sizeMat img

objectPos :: [Int] -> [Int] -> [Int]
objectPos [cropX,cropY] [offsetX,offsetY]
  = [cropX+offsetX+2, cropY+offsetY+2]

-------------------------------------------------------------
--                SDF process network                      --
-------------------------------------------------------------

-- | SDF process network chaining a series of image processing
-- algorithms upon a stream of pixel values originating from a set of
-- <https://en.wikipedia.org/wiki/Netpbm_format PPM images>.
imageProcessing :: Int
                -> Int
                -> Signal Int  -- ^ Input stream of pixel values
                -> Signal Int 
imageProcessing dimX dimY img = detect
  where
    grayed   = graySDF img
    offset   = getOffsetSDF $ xcorr2SDF $ cropSDF coords grayed
    coords   = calcCoordSDF previous grayed
    detect   = calcPosSDF coords offset
    previous = delaySDF init_tokens detect
    ----------------------------------------------------------------
    graySDF      = actor11SDF    (x0 * y1) (x1 * y1) grayF
    cropSDF      = actor21SDF (2, x1 * y1) (x2 * y2) cropF
    xcorr2SDF    = actor11SDF    (x2 * y2) (x3 * y3) xcorr2F
    getOffsetSDF = actor11SDF    (x3 * y3)        2  getOffsetF
    calcCoordSDF = actor21SDF (2, x1 * y1)        2  calcCoordF
    calcPosSDF   = actor21SDF (2,       2)        2  objectPos
    ----------------------------------------------------------------
    grayF        = fromMatrix .       grayscale . matrix x0 y1
    cropF c      = fromMatrix .          crop c . matrix x1 y1 
    xcorr2F      = fromMatrix . xcorr2 xPATTERN . matrix x2 y2
    getOffsetF   =                       posMax . matrix x3 y3
    calcCoordF p =                  calcCoord p . matrix x1 y1
    ----------------------------------------------------------------
    init_tokens = [dSPAN, dSPAN]
    x0 = dimX * 3
    x1 = dimX
    y1 = dimY
    x2 = cropSIZE
    y2 = cropSIZE
    x3 = x2 - 4
    y3 = y2 - 4
