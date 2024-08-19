## compiler 

g++ -o snowflake_client snowflake_client.cpp -I/usr/local/include -L/usr/local/lib -lthrift

g++ -o snowflake_client snowflake_client.cpp gen-cpp/Snowflake.cpp -I/usr/local/include -L/usr/local/lib -lthrift
