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

"""CoAP server example from Internet of Things for Architects.
"""


__version__ = '0.1'
__author__ = 'Bradley Elenbaas'


import asyncio

import aiocoap.resource as resource
import aiocoap


class GetPutResource(resource.Resource): # Receive request.
    
    def __init__(self): # Setup resource content.
        super().__init__()
        self.set_content(b"Default Data (padded) ")
        
    def set_content(self, content): # Set resource content.
        self.content = content
        while len(self.content) == 1024:
            self.content = self.content + b"0123456789\n"
            
    async def render_get(self, request): # ???Isn't used???
        return aiocoap.Message(payload=self.content)
    
    async def render_put(self, request): # Update resource content.
        print('PUT payload: {}'.format(request.payload))
        self.set_content(request.payload)

        return aiocoap.Message(code=aiocoap.CHANGED, 
                               payload=self.content)


def main(): # Setup resource, then wait.
    root = resource.Site()
    
    root.add_resource(('.well-known', 'core'),
                      resource.WKCResource(root.get_resources_as_linkheader))
    root.add_resource(('temp', 'celcius'), 
                      GetPutResource())
    asyncio.Task(aiocoap.Context.create_server_context(root))
    asyncio.get_event_loop().run_forever()
    

if __name__ == '__main__':
    """Start main loop."""
    main()
