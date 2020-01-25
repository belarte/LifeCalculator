import pytest

import subprocess
import asyncio
import websockets

async def exit():
    uri = "ws://localhost:8970"
    async with websockets.connect(uri) as websocket:
        await websocket.send('ctrl: exit')
        ack = await websocket.recv()
        assert ack.strip('\x00') == "ctrl: shutdown"

def test_backend():
    process = subprocess.Popen(['../bin/app/life-calculator'])

    asyncio.get_event_loop().run_until_complete(exit())

    process.wait()
    assert process.returncode == 0
