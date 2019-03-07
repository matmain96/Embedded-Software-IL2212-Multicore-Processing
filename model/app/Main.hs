-----------------------------------------------------------------------------
-- |
-- Module      :  Main
-- Copyright   :  (c) George Ungureanu, 2019
-- License     :  BSD3
-- 
-- Maintainer  :  ugeorge@kth.se
-- Stability   :  stable
-- Portability :  portable
--
-- Contains the main runner calling the testbench of this project.
-----------------------------------------------------------------------------
module Main where

import System.Console.GetOpt
import System.IO
import System.Exit
import System.Environment
import System.Directory
import Data.List (sort, isSuffixOf, intercalate, nub)


import ForSyDe.Shallow

import Tracker
import Utilities

-- | The main function, calling the testbench for the
-- 'Tracker.imageProcessing' process network.
--
-- Usage in an interpreter session:
--
-- > :main path/to/image-collection
main = do
  (opts,color,path) <- getArgs >>= parse
  files <- listDirectory (head path)
  let ppmFiles   = sort $ filter (isSuffixOf ".ppm") files
      inputPaths = checkEmpty $ map (\f->head path ++ "/" ++ f) ppmFiles
      checkEmpty [] = error  "the directory does not contain PPM files"
      checkEmpty a  = a
  (x, y, imgs) <- readAllPPM inputPaths
  let positions = splitEvery 2 $ fromSignal $ imageProcessing x y $ signal imgs

  -----------------------------------------------------
  mapM_ (printOut color x y inputPaths imgs positions) opts


printOut _ _ _ _ _ coords Coordinates = putStrLn $ intercalate "\n" $ map show coords
printOut _ x y paths imgs _ PrintInput   = do
  let imgBuffs = map (matrix (x*3) y) $ splitEvery (x*y*3) imgs
      grayed   = map grayscale imgBuffs
      printImg (path,img) = do { putStrLn path; printAscii 255 img; putStrLn "\n" }
  mapM_ printImg $ zip paths grayed
printOut color x y paths imgs coords PrintOutput = do
  let imgBuffs = map (matrix (x*3) y) $ splitEvery (x*y*3) imgs
      grayed   = map grayscale imgBuffs
      hidden   = zipWith hide coords grayed
      censorM  = matrix 9 9 $ replicate 81 (fromIntegral color)
      hide [x,y] img = replaceMat (x-4) (y-4) censorM img
      printImg (path,c,img) = do { putStrLn (path ++ show c); printAscii 255 img; putStrLn "\n" }
  mapM_ printImg $ zip3 paths coords hidden
  

--------------------------------------------

data Flag
  = Coordinates  -- -c --coords
  | PrintInput   -- -i --inputs
  | PrintOutput  -- -o --hidden
  | Color String --    --color
  | Help         -- -h --help
  deriving (Eq,Ord,Show)
 
flags =
  [Option ['c'] ["coords"] (NoArg Coordinates)
    "Prints the detection coordinates (default)"
  ,Option ['i'] []         (NoArg PrintInput)
    "Prints the grayed-out input images in ASCII art"
  ,Option ['o'] []         (NoArg PrintOutput)
    "Prints the grayed-out processed images in ASCII art"
  ,Option []    ["color"]  (ReqArg Color "GRAY_VAL")
    "Gray value of the hiding patch (default=0, i.e. black)"
  ,Option ['h'] ["help"]   (NoArg Help)
    "Print this help message"
  ]
  
parse argv
  = case getOpt Permute flags argv of
      (args,path,[]) -> do
        let options =
              let ops = concatMap (\x->filter (==x) args) [Coordinates, PrintInput, PrintOutput]
              in if null ops then [Coordinates] else nub ops
            color =
              let n = filter isColor args
                  isColor (Color _) = True
                  isColor _ = False
                  getColor (Color c : _) = read c :: Int
                  getColor [] = 0 :: Int
                  val = getColor n
              in if val < 0 || val > 255
                 then error $ "Value " ++ show val ++ "does not correspond to a grayscale level!"
                 else val
        if Help `elem` args
          then do hPutStrLn stderr (usageInfo header flags)
                  exitWith ExitSuccess
          else return (options,color,path)
      (_,_,errs)   -> do
        hPutStrLn stderr (concat errs ++ usageInfo header flags)
        exitWith (ExitFailure 1)
  
  where header = "Usage: il2212-track [-cioh|--color] PATH\nDetect a specific moving shape in a set of image frames.\n\nPATH is the path to a folder containing PPM images with the same dimensions,\n     sorted in alphabetical order.\nOptions:"
 
