provider "aws" {
  region = "eu-central-1"
}

resource "aws_security_group" "instance" {

}

resource "aws_launch_configuration" "example" {

}

resource "aws_autoscaling_group" "example" {
  launch_configuration = aws_launch_configuration.example

}

resource "aws_lb" "example" {
  name = "terraform-asg-wordpress-lb"
  load_balancer_type = "applicaiton"

}

resource "aws_lb_listener" "http" {
  port  = aws_lb.example.arn
  port  = var.port
  load_balancer_arn = ""
}

resource "aws_security_group" "alb" {
  ingress {
    from_port = 0
    protocol = ""
    to_port = 0
  }

  egress {
    from_port = 0
    protocol = ""
    to_port = 0
  }
}

resources "aws_lb_target_group" "asg" {

}

resources "aws_lb_listener_rule" "asg" {
  listener_arn = aws_lb_listener.arn

  condition {

  }



}