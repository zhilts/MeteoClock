from http.server import BaseHTTPRequestHandler, HTTPServer
import logging
import os

PORT = int(os.environ.get('ENV_VARIABLE_NAME') or '8000')


class RequestHandler(BaseHTTPRequestHandler):
    def do_POST(self):
        content_length = int(self.headers['Content-Length'])
        request_body = self.rfile.read(content_length).decode('utf-8')
        logging.info('Received POST request with body: %s', request_body)

        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        self.wfile.write(b'Successfully logged the request body')

    def log_message(self, format, *args):
        # Disable the default request logging
        pass


def run_server():
    logging.basicConfig(level=logging.INFO)
    server_address = ('', PORT)
    httpd = HTTPServer(server_address, RequestHandler)
    print(f'Starting the server on http://localhost:{PORT}')
    httpd.serve_forever()


run_server()
