"""
Main module for Arduino CLI MCP Server.
Contains the Arduino CLI Server implementation and MCP server functions.
"""

from typing import Sequence, Dict, Optional, List
import json
import subprocess
import shlex
import os
import tempfile
import re
import argparse

from mcp.server import Server
from mcp.server.stdio import stdio_server
from mcp.types import Tool, TextContent, ImageContent, EmbeddedResource
from mcp.shared.exceptions import McpError
from pydantic import BaseModel, Field

# Import all the classes and code from the original main.py
# (Copy all the class definitions and functions here)
# ...

# Make sure to keep the main function and async serve function

def main():
    import asyncio
    
    # Parse command line arguments
    parser = argparse.ArgumentParser(description="Arduino CLI MCP Server")
    parser.add_argument('--workdir', type=str, default=None,
                        help='Working directory for Arduino sketches and projects')
    args = parser.parse_args()
    
    # Validate workdir
    if args.workdir and not os.path.exists(args.workdir):
        print(f"Warning: Specified workdir '{args.workdir}' does not exist. Will try to create it.")
    
    print(f"Starting Arduino CLI MCP server with workdir: {args.workdir or 'current directory'}")
    asyncio.run(serve(workdir=args.workdir))

if __name__ == "__main__":
    main()
