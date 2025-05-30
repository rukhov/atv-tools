import os, tempfile, logging
from pathlib import Path
import re

log = logging.getLogger('bw_secam_productivity')

def test_bw_secam_productivity(projectPath, decoderPath):

    tmpFolder = Path( tempfile.gettempdir() )
    inputFile = Path( projectPath + '/test-data/cartoon-test-video-4-16000000Hz.i16')
    aviOutputFile = tmpFolder.joinpath(inputFile.stem).with_suffix(".avi")

    tmpFolder.mkdir(0o777, True, True)

    child = os.popen(decoderPath + 
            " --input-type i16"
            " --input-data-type cvbs"
            " --output-type avi"
            " --standard secam"
            " --input-file " + str(inputFile) +
            " --output-file " + str(aviOutputFile) +
            " --sample-rate 16000000"
            " --dc-correction .0"
            " --amplification 1.333"
            " --bw true"
            " --max-frames 0"
            )

    out = child.read()

    m = re.search(r'Productivity: (\d+\.\d+) FPS.', out)

    log.info(f"outout: {out}")

    log.info(f"Productivity: {m.groups()[0]}")

    #assert float(m.groups()[0]) < 45
    assert float(m.groups()[0]) > 1