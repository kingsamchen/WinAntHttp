#! python3
# -*- coding: utf-8 -*-
# 0xCCCCCCCC

from flask import Flask, request, Response

app = Flask('__name__')

PASSED = 'passed'
FAILED = 'failed'


def new_passed_response():
    return Response(PASSED, status=200)


def new_failed_response():
    return Response(FAILED, status=400)


@app.route('/', methods=['GET', 'POST'])
def root():
    greeting = 'Welcome to mock server via {0}'.format(request.method)
    return greeting


@app.route('/query-string', methods=['GET'])
def query_string():
    value = request.args.get('key')
    sole_key = request.args.get('solekey', '')
    if value == 'value' and sole_key == '':
        return new_passed_response()
    else:
        return new_failed_response()


@app.route('/escape-test', methods=['GET', 'POST'])
def escape_validate():
    method = request.method
    if method == 'GET':
        recv_data = request.args['data']
    elif method == 'POST':
        recv_data = request.form['data']
    else:
        raise NotImplementedError

    if recv_data == '!@#$%^&*()_-=+~`,.<>/?;:[]{}|\ ':
        return new_passed_response()
    else:
        print('received: ' + recv_data)
        return new_failed_response()


@app.route('/empty-query-string', methods=['GET'])
def empty_query_string():
    empty = len(request.args) == 0
    if empty:
        return new_passed_response()
    else:
        print('query-string is not empty: ' + str(request.args))
        return new_failed_response()


@app.route('/url-encoded-content', methods=['POST'])
def url_encoded_content():
    content = request.form
    if content['type'] == 'urlencoded' and \
       content['category'] == 'test' and \
       'data' in content:
        return new_passed_response()
    else:
        return new_failed_response()


def validate_basic_headers(headers):
    if len(headers) != 0:
        if headers.get('category', '') == 'test' and \
           headers.get('buvid', '') == '0xDEADBEEF' and \
           headers.get('expires', '') == '2020-01-01':
            return True
        else:
            return False


@app.route('/basic-headers', methods=['GET', 'POST'])
def basic_headers():
    if validate_basic_headers(request.headers):
        return new_passed_response()
    else:
        print('received headers: ' + str(request.headers))
        return new_failed_response()


@app.route('/json-test', methods=['POST'])
def json_test():
    """
    test data:
        {
            "zoomLevel": 0,
            "trimOnSave": true,
            "colorTheme": "Visual Studio Dark"
        }
    """
    print(request.headers.get('Content-Type'))
    print(request.get_json(force=True))
    if request.headers.get('Content-Type') == 'application/json':
        content = request.get_json()
        if content.get('zoomLevel') == 0 and \
           content.get('trimOnSave') is True and \
           content.get('colorTheme') == 'Visual Studio Dark':
            return new_passed_response()
    return new_failed_response()


def main():
    app.run()


if __name__ == '__main__':
    main()
