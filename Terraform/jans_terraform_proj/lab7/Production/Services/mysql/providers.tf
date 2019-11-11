provider "aws" {
  region = "eu-central-1"
}
# Configure the MySQL provider based on the outcome of
# creating the aws_db_instance.
//provider "mysql" {
//  endpoint = "${aws_db_instance.default.endpoint}"
//  username = "${aws_db_instance.default.username}"
//  password = "${aws_db_instance.default.password}"
//}
