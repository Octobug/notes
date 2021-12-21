import asyncio


async def start_io(ident):
    print(f"{ident} blocking")
    # 模拟I/O操作
    await asyncio.sleep(2)
    print(f"{ident} wake up")


async def say_hello(ident):
    print(f"{ident}：hello,")
    await start_io(ident)
    print(f"i'm {ident}")

loop = asyncio.get_event_loop()
loop.create_task(say_hello('Ming'))
loop.create_task(say_hello('Hong'))
loop.run_forever()
