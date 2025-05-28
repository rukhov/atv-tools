import pytest, sys, logging, pathlib

log = logging.getLogger('conftest')

def pytest_addoption(parser):
    parser.addoption("--projectPath", action="store", default="")
    parser.addoption("--assetsPath", action="store", default="")
    parser.addoption("--executablesPath", action="store", default="")

def _executableSuffix():
    if sys.platform == 'win32':
        return '.exe'
    else:
        return ''

@pytest.fixture(scope="session")
def assetsPath(pytestconfig):
    return pytestconfig.getoption("assetsPath")

@pytest.fixture(scope="session")
def projectPath(pytestconfig):
    prjPath:str = pytestconfig.getoption('projectPath')
    if len(prjPath) == 0:
        path:pathlib.PosixPath = pytestconfig.invocation_params.dir
        prjPath = str(path.parent)
        log.info(f"projectPath is empty, defaulting to: {prjPath}")
    return prjPath

@pytest.fixture(scope="session")
def executablesPath(pytestconfig):
    return pytestconfig.getoption("executablesPath")

@pytest.fixture(scope="session")
def executableSuffix():
    return _executableSuffix()

@pytest.fixture(scope="session")
def decoderPath(pytestconfig):
    decoderPath:str = pytestconfig.getoption("executablesPath")
    if len(decoderPath) == 0:
        path:pathlib.PosixPath = pytestconfig.invocation_params.dir
        decoderPath = str(path.parent.parent) + '/build/bin'
        log.info(f"decoderPath is empty, defaulting to: {decoderPath}")
    return decoderPath + '/atv-tools-cli' + _executableSuffix()
