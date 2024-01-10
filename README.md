# 42-webserv

Welcome to 42-webserv, a powerful and lightweight C++ web server inspired by Nginx. This web server is designed to handle HTTP requests with a focus on simplicity, performance, and extensibility. Whether you're hosting a static website or building a dynamic application, 42-webserv has you covered.

## Features

- **Configuration Flexibility:** Define your server's behavior precisely using a configuration file. Customize virtual server contexts and fine-tune settings for different locations within those servers.

- **Supported HTTP Methods:** 42-webserv supports the following HTTP methods: GET, POST, DELETE. Handle various types of requests seamlessly.

- **Server Directives:**
  - **listen:** Specify IP and port for the server to bind to.
  - **root:** Define the root path of the server directory.
  - **server_name:** Set names that HTTP clients can send via the Host header in HTTP requests.
  - **allow_methods:** Specify allowed HTTP methods for this server.
  - **upload_dir:** Define the directory where the server should store files from multipart form data.
  - **error_page:** Configure custom error pages based on response status codes.
  - **return:** Set up redirection URLs for specific scenarios.

- **Makefile Usage:**
  - `make`: Build the 42-webserv.
  - `make re`: Rebuild the 42-webserv.
  - `make clean`: Clean object files.
  - `make fclean`: Clean object files and the executable.

## Getting Started

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/davitmartirosyan/42-yerevan-webserv.git
   cd 42-webserv

## Example Server Configuration

```
server {
    listen 127.0.0.1:8080;
    root /path/to/www;
    server_name example.com www.example.com;
    allow_methods GET POST;
    upload_dir /path/to/uploads;
    error_page 404 /404.html;
    return 301 https://example.com$request_uri;
    
    location /api {
        allow_methods GET POST DELETE;
        root /path/to/api;
        error_page 500 /500.html;
    }
}

```