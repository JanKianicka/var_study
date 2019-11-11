

provider "aws" {
  region = "eu-central-1"
}

# Bucket is something like directory of target file system
# where e.g. data can be stored
resource "aws_s3_bucket" "main" {
  bucket = "terraform-backend-jan"
  acl = "private"
  tags = {
    Name = "Bucket for TEState"
    Environment = "Dev"
  }
  # If bucket is not empty it is not possible to destroy it
  # unless we force it like this
  force_destroy = true
}
