
paths = ["../test/test-ppm/circ1.ppm","../test/test-ppm/circ2.ppm", "../test/test-ppm/circ3.ppm", "../test/test-ppm/circ4.ppm" ]
(x,y,imgs) <- readAllPPM paths
imageProcessing x y $ signal(imgs)
