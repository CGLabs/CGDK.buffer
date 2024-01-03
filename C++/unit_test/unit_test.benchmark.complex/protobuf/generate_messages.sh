PATH_NAME=$(dirname $(realpath $0))
protoc messages_test.proto --cpp_out=./
