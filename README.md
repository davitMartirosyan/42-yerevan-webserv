# 42-yerevan-webserv

Welcome to **42-yerevan-webserv**, an advanced C++ web server designed with the spirit of Nginx. This web server provides a robust platform for hosting your web applications, offering flexibility, performance, and extensibility.

## Special Thanks

Many thanks to my friend [Vahan](https://github.com/vahannn) for their invaluable contributions and collaborative efforts in building this project.

Feel free to contribute, report bugs, or share your ideas by opening an issue or submitting a pull request.

Happy coding with 42-yerevan-webserv! 🚀


## Features

- **Configuration Mastery:** Customize your server's behavior precisely using a powerful configuration file. Define virtual server contexts and fine-tune settings for different locations within those servers.

- **Supported HTTP Methods:** 42-yerevan-webserv proudly supports essential HTTP methods: GET, POST, DELETE. Empower your applications with versatile request handling.

- **Server Directives:**
  - `listen`: Specify the IP and port for the server to bind to.
  - `root`: Set the root path of the server directory.
  - `server_name`: Specify names that HTTP clients can send via the Host header in HTTP requests.
  - `allow_methods`: Explicitly define allowed HTTP methods for this server.
  - `upload_dir`: Configure the directory where the server should store files from multipart form data.
  - `error_page`: Craft custom error pages based on response status codes.
  - `return`: Set up redirection URLs for specific scenarios.	
  - `cgi`: Enable CGI script execution for handling Python and PHP scripts.

- **Makefile Mastery:**
  - `make`: Build 42-yerevan-webserv.
  - `make re`: Rebuild 42-yerevan-webserv.
  - `make clean`: Purge object files.
  - `make fclean`: Clean object files and the executable.

## Getting Started

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/your-username/42-yerevan-webserv.git
   cd 42-yerevan-webserv

# Example Configuration File

```
server {
    listen 127.0.0.1:8080;
    root /path/to/www;
    server_name example.com www.example.com;
    allow_methods GET POST;
    upload_dir /path/to/uploads;
    error_page 404 /404.html;
    return 301 https://example.com$request_uri;
    cgi php /path/to/php-cgi;
	
    location /api {
        allow_methods GET POST DELETE;
        root /path/to/api;
        error_page 500 /500.html;
    }
}

```