/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 00:33:26 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/01 21:55:42 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lib.hpp"
#define PORT 8080
std::string responseBody(std::string body);
HttpMetaProvider Meta;
const int MAX_BUFFER_SIZE = 1024;

int main(int ac, const char**av, const char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;
	int len = sizeof(addr);
	int opt = 1;
	char http[MAX_BUFFER_SIZE];
	size_t valread;
	std::string response;
	setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(PORT);
	bind(server_socket, (struct sockaddr*)&addr, sizeof(addr));
	listen(server_socket, 3);
	
	while (1)
	{
		int accept_socket = accept(server_socket, (struct sockaddr*)&addr, (socklen_t*)&len);
		std::string request = "";
		int	bytes = read(accept_socket, http, MAX_BUFFER_SIZE);
		request += http;
		std::memset(http, 0, sizeof(http));
		
		if (!request.empty())
		{
			HttpRequest req(request);
			std::string path = req.url();
			if (path == "/")
				path += "index.html";
			std::string realPath = "tmp/www/" + path;
			response += "HTTP/1.1 200 OK\r\n";
			response += "Connection: close\r\n";
			response += "Content-Type: " + Meta.mimeType(realPath) + "\r\n";
			response += "\r\n";
			response += responseBody(realPath);
			send(accept_socket, response.c_str(), response.size(), 0);
		}
		response.erase();
		close(accept_socket);
		write(1, request.c_str(), request.size());
		write(1, "\n", 1);
	}
}


std::string responseBody(std::string path)
{
	std::fstream index;
	std::string line;
	std::string content;
	index.open(path.c_str());
	if (index.is_open())
	{
		while (getline(index, line, '\0')){
			content += line;
		}
		index.close();
		return (content);
	}
	return ("<h1>404</h1>");

}
