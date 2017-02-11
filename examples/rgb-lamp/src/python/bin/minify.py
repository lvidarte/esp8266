#!/usr/bin/env python

"""
Usage:
    python3 minify.py > template.py
"""

TEMPLATE_FILE = 'template.html'

with open(TEMPLATE_FILE) as f:
    html = ' '.join(' '.join(f.readlines()).split())
    html = html.replace('> <', '><')
    html = html.replace('> ', '>')
    html = html.replace('< ', '<')
    html = html.replace(' { ', '{')
    html = html.replace(' } ', '}')
    html = html.replace(' + ', '+')
    html = html.replace(' = ', '=')
    html = html.replace(', ', ',')
    html = html.replace('; ', ';')
    html = html.replace(': ', ':')
    html = html.replace(' /', '/')
    print('html = """' + html + '"""')
