# Creating complete infrastructure on AWS
# 1. Creating resources
resource "aws_vpc" "main" {
  cidr_block       = "10.0.0.0/16"
  instance_tenancy = "dedicated"

  tags = {
    Name = "main"
  }
}

resource "aws_internet_gateway" "mygateway" {

}

/*resource "aws_api_gateway_rest_api" "MyDemoAPI" {
  name        = "MyDemoAPI"
  description = "This is my API for demonstration purposes"
}

resource "aws_api_gateway_resource" "MyDemoResource" {
  rest_api_id = "${aws_api_gateway_rest_api.MyDemoAPI.id}"
  parent_id   = "${aws_api_gateway_rest_api.MyDemoAPI.root_resource_id}"
  path_part   = "mydemoresource"
}*/

# Two VPC private subnets
resource "aws_subnet" "main1" {
  vpc_id     = "${aws_vpc.main.id}"

  cidr_block = "10.0.0.1/24"
  # CIDR block -
  availability_zone = ""
  map_public_ip_on_launch = true

  tags = {
    Name = "Main"
  }
}

resource "aws_subnet" "private" {
  vpc_id     = "${aws_vpc.main.id}"
  cidr_block = "10.0.0.2/24"

  tags = {
    Name = "Main"
  }
}

# purchased IP address - static IP address -
resource "aws_eip" "nat" {
  count = lenght(var.availibility_zones)
  vpc = true
}

resource "aws_nat_gateway" "gw" {
  allocation_id = "${aws_eip.nat.id}"
  subnet_id     = "${aws_subnet.public.id}"

  tags = {
    Name = "gw NAT"
  }
}

resource "aws_route_table" "r" {
  vpc_id = "${aws_vpc.default.id}"

  route {
    cidr_block = "10.0.1.0/24"
    gateway_id = "${aws_internet_gateway.main.id}"
  }

  route {
    ipv6_cidr_block        = "::/0"
    egress_only_gateway_id = "${aws_egress_only_internet_gateway.foo.id}"
  }

  tags = {
    Name = "main"
  }
}
