import argparse
import os

parser = argparse.ArgumentParser(description="Builds up a gif with the results of il2212's lab.")
parser.add_argument('coordinates', type=str, nargs='+', help='coordinates of identified object')
parser.add_argument('-c', '--hide-color', default='000000', type=str, help='Hex number for RGB value of the hiding patch')
parser.add_argument('-i', '--input-folder', default='.', type=str, help='path to the folder contaning ppms')
parser.add_argument('-o', '--output-folder', default='out', type=str, help='path to the folder to output ppms')

args = parser.parse_args()
hideR = int(args.hide_color[0:2],16)
hideG = int(args.hide_color[2:4],16)
hideB = int(args.hide_color[4:6],16)

ppms = [f for f in os.listdir(args.input_folder) if '.ppm' in f]
print('*** Running over {0} ppms and outputing in {1}'.format(len(ppms), args.output_folder))
try:
    os.makedirs(args.output_folder)
except:
    pass
spots = []
for line in args.coordinates:
    if line:
        a, b = line.strip('[').strip(']').split(',')
        a = int(a)
        b = int(b)
        spots.append((a,b))
for (idx, ppm) in enumerate(sorted(ppms)):
    with open(os.path.join(args.input_folder, ppm), 'r') as ppmf:
        values = ppmf.read().splitlines()
        if values[1].startswith('#'):
            values=values[0:1] + values[2:]
        values = ' '.join(values).split()
        kind = values[0]
        values = map(int, values[1:])
        w, h, maxval = values[0:3]
        values = values[3:]
        for x in range(spots[idx][0]-3, spots[idx][0]+4):
            for y in range(spots[idx][1]-3, spots[idx][1]+4):
                values[3*x + 3*w*y + 0] = hideR
                values[3*x + 3*w*y + 1] = hideG
                values[3*x + 3*w*y + 2] = hideB
        with open(os.path.join(args.output_folder, ppm), 'w') as ppmfo:
            ppmfo.write('{0}\n{1}\n{2}\n{3}\n'.format(kind, w, h, maxval))
            for elem in values:
                ppmfo.write('{0}\n'.format(elem))
print('*** Done')
