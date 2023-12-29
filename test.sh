#!/bin/bash

# Define an array of hostnames to test
hostnames=("example.com" "test.com" "anotherdomain.com")

# Loop through each hostname and perform cURL requests
for host in "${hostnames[@]}"
do
    echo "Testing $host"
    # Perform cURL request with the specific hostname and check the response
    curl_output=$(curl --resolve "$host:8080:127.0.0.1" "http://$host/")
    
    # Check the response, you can add more complex checks based onyour server's expected behavior
    if [[ "$curl_output" == *"<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><link rel='shortcut icon' href='data:image/x-icon;,' type='image/x-icon'><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">
    <title>Document</title><style>body{display:flex;justify-content: center;align-items: center;}</style></head><body><h1>404</h1></body></html>"* ]]; then
        echo "Success: $host is working as expected"
    else
        echo "Error: $host is not responding as expected"
        # You might want to log this or handle errors accordingly
    fi
done

