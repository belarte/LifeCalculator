import pytest

import subprocess
import asyncio
import websockets

@pytest.fixture
def app():
    process = subprocess.Popen(['../bin/app/life-calculator'])
    yield process
    process.wait()
    assert process.returncode == 0

def test_connect_and_disconnect():
    process = subprocess.Popen(['../bin/app/life-calculator'])

    async def exit():
        uri = "ws://localhost:8970"
        async with websockets.connect(uri) as websocket:
            await websocket.send('ctrl: exit')
            ack = await websocket.recv()
            assert ack.strip('\x00') == "ctrl: shutdown"

    loop = asyncio.new_event_loop()
    loop.run_until_complete(exit())
    loop.close()

    process.wait()
    assert process.returncode == 0

def test_setup_with_0_returns_empty_board(app):
    async def setup_0():
        uri = "ws://localhost:8970"
        async with websockets.connect(uri) as websocket:
            await websocket.send('app: expr=0')
            ack = await websocket.recv()
            assert ack.strip('\x00') == "app: nothing"
            await websocket.send('ctrl: exit')
            ack = await websocket.recv()
            assert ack.strip('\x00') == "ctrl: shutdown"

    loop = asyncio.new_event_loop()
    loop.run_until_complete(setup_0())
    loop.close()

def test_setup_with_1_returns_one_glider(app):
    async def setup_1():
        uri = "ws://localhost:8970"
        async with websockets.connect(uri) as websocket:
            await websocket.send('app: expr=1')
            ack = await websocket.recv()
            assert ack.strip('\x00') == "app: data: x = 3, y = 3\nbo$2bo$3o!"
            await websocket.send('ctrl: exit')
            ack = await websocket.recv()
            assert ack.strip('\x00') == "ctrl: shutdown"

    loop = asyncio.new_event_loop()
    loop.run_until_complete(setup_1())
    loop.close()
