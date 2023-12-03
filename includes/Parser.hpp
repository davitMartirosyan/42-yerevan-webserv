/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 00:25:27 by dmartiro          #+#    #+#             */
/*   Updated: 2023/12/04 00:17:50 by dmartiro         ###   ########.fr       */
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
    private:
    enum p_type
    {
        WORD, // general type of token for CONTEXT && DIRECTIVE
        CONTEXT, // for server and location contexts
        OPENBRACE,
        CLOSEBRACE,
        DIRECTIVE,
        DIRECTIVE_VALUE,
        SEMICOLON,
        CONTEXT_PREFIX, //For location context
        SEPARATOR
    };
    public:
        Parser(std::string const &confFile);
        ~Parser();
    public:
        void start(ServerManager const *mgn);
    private:
        bool isContext(std::string const &line);
        bool isDirective(std::string const &line);
        size_t contextWord(std::string const &config, size_t p);
        size_t contextOpen(std::string const &config, size_t p);
        bool isWord(char s);
        void addWord(std::string const &config, size_t *i);
        void addToken(char s, p_type type);
        std::string trim_comments();
        void semantics(std::string const &config);
        void correction( void );
    private:
        std::fstream IO;
        std::vector<std::string>context;
        std::vector<std::string>directives;
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