import os, logging
import tempfile
from pathlib import Path
import re

log = logging.getLogger('test_decode_secam_cartoon_4')

def test_decode_secam_cartoon_4(projectPath, decoderPath):

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
            " --max-frames 0"
            )

    out = child.read()

    log.info(f"Output: {out}")

    m = re.search(r'Total frame number: (\d+)', out)

    assert int(m[1]) >= 153
