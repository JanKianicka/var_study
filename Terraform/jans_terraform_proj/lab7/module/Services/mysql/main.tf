provider "aws" {
  region = "eu-central-1"
}

# Create a database server
resource "aws_db_instance" "default" {
  engine         = "mysql"
  engine_version = "5.7"
  instance_class = "db.t2.micro"
  name           = "initial_db_jan"
  allocated_storage = 50
  username       = var.username
  password       = var.password
  # in order to make the db instances public there should be configured dedicated security group which will expose ports
  # vpc_security_group_ids = []

}