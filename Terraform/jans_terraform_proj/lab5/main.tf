provider "aws" {
  region = "eu-central-1"
}

resource "aws_security_group" "instance" {
  name = "terraform-example-instance-jan"

  ingress {
    from_port = 80
    to_port   = 80
    protocol  = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }
}

resource "aws_launch_configuration" "example"{
  image_id = "ami-01e8fb9918c3b3eb2"
  instance_type = "t2.micro"
  security_groups = [aws_security_group.instance.id]
  # New instance will be created and destroyed before craetion of the next one
  lifecycle {
    create_before_destroy = true
  }
}

resource "aws_autoscaling_group" "bar" {
  name                 = "terraform-asg-example"
  launch_configuration = aws_launch_configuration.example.name
  vpc_zone_identifier = data.aws_subnet_ids.default.ids
  min_size             = 2
  max_size             = 10

/*  lifecycle {
    create_before_destroy = true
  }*/

  tag {
    key  = "Name"
    value = "terraform-asg-wordpress-jan"
    propagate_at_launch = true
  }
}