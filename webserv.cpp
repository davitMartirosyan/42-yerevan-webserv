/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 00:33:26 by dmartiro          #+#    #+#             */
/*   Updated: 2023/09/30 23:41:33 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lib.hpp"
#define PORT 8080
std::string responseBody(std::string body);
HttpMetaProvider Meta;

int main(int ac, const char**av, const char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;
	int len = sizeof(addr);
	int opt = 1;
	size_t valread;
	char http[1028] = {0};
	std::string response;
	(void)valread;
	setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(PORT);
	bind(server_socket, (struct sockaddr*)&addr, sizeof(addr));
	listen(server_socket, 3);
	while (1)
	{
		int accept_socket = accept(server_socket, (struct sockaddr*)&addr, (socklen_t*)&len);
		valread = recv(accept_socket, http, 1028, 0);
		
		std::string request = http;
		/////////Parsing Request/////////////
		/////////////////////////////////

		if (!request.empty())
		{
			HttpRequest req(request);
			std::string path = req.url();
			std::string realPath = "tmp/www";
			if (path == "/")
				path += "index.html";
			realPath += path;
			response += "HTTP/1.1 200 OK\r\n";
			response += "Connection: close\r\n";
			response += "Content-Type: " +  Meta.mimeType(realPath) + "\r\n\r\n";
			response += responseBody(realPath);
			send(accept_socket, response.c_str(), response.size(), 0);
		}
		response.erase();
		close(accept_socket);
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
