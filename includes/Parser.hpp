/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 00:25:27 by dmartiro          #+#    #+#             */
/*   Updated: 2023/12/02 20:03:06 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
#define PARSER_HPP
#include "Libs.hpp"
#include "ServerManager.hpp"

class HTTPRequest;
class ServerManager;
class Parser
{
    public:
        Parser(std::string const &confFile);
        ~Parser();
    public:
        void start(ServerManager const *mgn);
    private:
        bool isContext(std::string const &line);
        bool isDirective(std::string const &line);
    private:
        std::fstream IO;
        std::vector<std::string>context;
        std::vector<std::string>directives;
    private:
        enum p_type
        {
            CONTEXT, // for server and location contexts
            OPENBRACE,
            CLOSEBRACE,
            DIRECTIVE,
            DIRECTIVE_VALUE,
            SEMICOLON,
            CONTEXT_PREFIX //For location context
        };
        struct Token
        {
            p_type type;
            std::string token;   
        };
        std::list<Token> tokens;
        std::stack<std::string> braces;
};

// server, location
//root, index, autoindex, error_page, methods, client_body_size, server_name, listen

#endif