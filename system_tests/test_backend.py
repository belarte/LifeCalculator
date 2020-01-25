import pytest
import subprocess

def test_backend():
    process = subprocess.Popen(['../bin/app/life-calculator'])
    process.wait()

    assert process.returncode == 0
