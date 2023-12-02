/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 00:25:27 by dmartiro          #+#    #+#             */
/*   Updated: 2023/12/02 18:24:32 by dmartiro         ###   ########.fr       */
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
        std::fstream IO;
        std::vector<std::string>context;
        std::vector<std::string>directives;
    private:
        std::stack<std::string> brace;
    private:
        bool isContext(std::string const &line);
        bool isDirective(std::string const &line);
        enum parser_tokens
        {
            CONTEXT, // for server and location contexts
            OPENBRACE,
            CLOSEBRACE,
            DIRECTIVE,
            DIRECTIVE_VALUE,
            SEMICOLON,
            CONTEXT_PREFIX //For location context
        };
};

// server, location
//root, index, autoindex, error_page, methods, client_body_size, server_name, listen



/*

                    NULL || } <- CONTEXT -> {
    CONTEXT_PREFIX <- CONTEXT { OPENBRACE -> DIRECTIVE
    
*/

#endif