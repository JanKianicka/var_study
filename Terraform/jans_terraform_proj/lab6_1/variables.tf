variable "instance_type" {
  type = "string"
  default = "t2.nano"
}

variable "region" {
  type = "string"
  description = "Common definition of AWS region "
}

variable "port" {
  type = number
}

# Other types of variables
# primitive types
# then list, set, map, object, tuple
# Object can have mixed tuped properties - there can be also list type in
# Then we have environmental variables

# referencing inside the terraform code
# [aws_security_group.instance.id] - <provider_type>.<name>.<attribute>
# this 'id' is replaced by the provider when we run apply.
# Terraform does not read line-by-line but craete dependency graph.