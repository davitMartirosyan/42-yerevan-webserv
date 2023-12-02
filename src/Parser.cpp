/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 00:30:12 by dmartiro          #+#    #+#             */
/*   Updated: 2023/12/02 18:20:46 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser(std::string const &confFile)
{
    context.push_back("server\0");
    context.push_back("location\0");

    directives.push_back("root");
    directives.push_back("index");
    directives.push_back("autoindex");
    directives.push_back("allow_methods");
    directives.push_back("error_page");
    directives.push_back("client_body_size");
    directives.push_back("listen");
    directives.push_back("server_name");

    
    IO.open(confFile.c_str(), std::ios::in);
    if (!IO.is_open())
        throw HTTPCoreException("Error: File not found");
}

Parser::~Parser()
{
    
}

void Parser::start(ServerManager const *mgn)
{
    std::string line;
    std::string config;
    bool contextFound = false;
    bool directiveFind = false;
    size_t comment = 0;
    while (std::getline(IO, line))
    {
        if (line.empty())
            continue;
        if ((comment = HTTPRequest::trim(line).find_first_of("#")) != std::string::npos)
        {
            line = line.substr(0, comment);
            config += (line.size() > 0) ? HTTPRequest::trim(line) : "";
        }
        else
            config += HTTPRequest::trim(line);
    }

    


std::cout << config << std::endl;
    // std::string character;
    // std::string charString;
    // std::vector<std::string> virtualServers;
    // for(size_t i = 0; i < config.size(); i++)
    // {
    //     if (config[i] == '{' && HTTPRequest::trim(charString) == "server")
    //     {
               
    //     }
    // }

    
}

bool Parser::isContext(std::string const &line)
{
    std::vector<std::string>::iterator it = std::find(context.begin(), context.end(), HTTPRequest::trim(line));
    if (it != context.end())
        return (true);
    return (false);
}

bool Parser::isDirective(std::string const &line)
{
    std::vector<std::string>::iterator it = std::find(directives.begin(), directives.end(), HTTPRequest::trim(line));
    if (it != directives.end())
        return (true);
    return (false);
}