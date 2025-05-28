import os, logging
from pathlib import Path
import tempfile
import re
import frame_checker as fc

log = logging.getLogger('test_decode_color_bars')

def test_decode_color_bars(projectPath, decoderPath):

    tmpFolder = Path( tempfile.gettempdir() )
    inputFile = Path( projectPath + '/test-data/cvbs-secam-colorbars-16000000Hz.i16')
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

    log.warning(f"Output: {out}")

    m = re.search(r'Total frame number: (\d+)', out)

    assert int(m[1]) > 8
    
    #check colors

    vc = fc.VideoColorChecker(str(aviOutputFile), 8) 
    assert vc.isOpen() == True

    tolerance = 20  # Tolerance value for color comparison

    assert vc.RelativeCheckAt( (0*(1/7)+1/14, 1/3) , (220, 220, 220) , tolerance) == True
    assert vc.RelativeCheckAt( (1*(1/7)+1/14, 1/3) , (220, 220,  10) , tolerance) == True
    assert vc.RelativeCheckAt( (2*(1/7)+1/14, 1/3) , ( 10, 220, 220) , tolerance) == True
    assert vc.RelativeCheckAt( (3*(1/7)+1/14, 1/3) , ( 10, 230,  10) , tolerance) == True
    assert vc.RelativeCheckAt( (4*(1/7)+1/14, 1/3) , ( 230, 10, 230) , tolerance) == True
    assert vc.RelativeCheckAt( (5*(1/7)+1/14, 1/3) , ( 230, 10,  10) , tolerance) == True
    assert vc.RelativeCheckAt( (6*(1/7)+1/14, 1/3) , (  10, 10, 230) , tolerance) == True

    assert vc.RelativeCheckAt( (0*(1/6)+1/12, 8/9) , ( 10,  30,  60) , tolerance) == True
    assert vc.RelativeCheckAt( (1*(1/6)+1/12, 8/9) , (220, 220, 220) , tolerance) == True
    assert vc.RelativeCheckAt( (2*(1/6)+1/12, 8/9) , ( 40,  10,  80) , tolerance) == True
    assert vc.RelativeCheckAt( (4*(1/6)+1/12, 8/9) , ( 10,  10,  10) , tolerance) == True
