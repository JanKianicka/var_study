provider "aws" {
  # region = "eu-central-1"
  # using variables
  region = var.region
}

terraform {
  required_version = ">= 0.12.10"

  backend "s3" {
    # this bucket does not exist
    bucket = "terraform-backend-jan"
    key = "lab3/terraform.tfstate"
    region = "eu-central-1"
    # region = var.region - in this block it is not allowed to use variables
    encrypt = "true"
  }
}


resource "aws_s3_bucket" "main" {
  bucket = "terraform-backend-jan2"
  acl = "private"
  tags = {
    Name = "Bucket for TEState2"
    Environment = "Dev"
  }
  # If bucket is not empty it is not possible to destroy it
  # unless we force it like this
  force_destroy = true
}
