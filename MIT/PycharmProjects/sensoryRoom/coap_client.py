"""
Copyright 2023 Bradley Elenbaas

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files
(the “Software”), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge,
publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
"""

"""CoAP client example from Internet of Things for Architects.
"""


__version__ = '0.1'
__author__ = 'Bradley Elenbaas'


import asyncio

from aiocoap import *


async def main(): # Send request, get response.
    context = await Context.create_client_context()
    
    await asyncio.sleep(2)
    
    payload = b"20.2 C"
    request = Message(code=PUT, payload=payload)
    
    request.opt.uri_host = '127.0.0.1'
    request.opt.uri_path = ("temp", "celcius")
    
    response = await context.request(request).response
    
    print('code:    {}'.format(response.code))
    print('payload: {}'.format(response.payload))
    


if __name__ == '__main__':
    """Start main."""
    asyncio.get_event_loop().run_until_complete(main())
