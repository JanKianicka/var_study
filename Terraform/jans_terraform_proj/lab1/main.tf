# this the definition of the terraform provider
# different cloud platform
# region - AWST has dived its cloud into different regions
# "availability zone" - eu-central-1 is in Frankfurt - there are Amazon resources
# closes region to you
provider "aws" {
  region = "eu-central-1"
}
# We can have also different providers
# provider "google" {}
# resource "google_app_engine_application" {
#
#}
#
# resource "PROVIDER_TYPE" "NAME_TO_BE_USED_IN_TERRAFORM"{
# }

# this is the instance
# resource - Amazon calls this as "services" - service by Amazon is resource for Terraform
# whatever you can run at Amazon
# aws_instance - virtual machine
# "helloWorld" is the name insite terraform
# they will become services insite the cloud - architect drow a diagram of the building
# "aws_instance" - aws_* is convention from terraform
resource "aws_instance" "helloWorld" {
  # ami - amazon image, bluprint of the machine which I want to launch
  ami = "ami-01e8fb9918c3b3eb2"
  # instance_type - defines how much power is needed for my machine
  # https://aws.amazon.com/ec2/instance-types/
  # Instance	vCPU*	CPU Credits/hour	Mem (GiB)	Storage	Network Performance (Gbps)
  # t3.micro	2       12                   1	           EBS-Only     Up to 5
  instance_type = "t2.micro"

  tags = {
    Name = "Jan's terraform plan."
  }
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

