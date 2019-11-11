module "example_elb" {
  source = "../../../module/Services/elb"
  instance_type = "t2.micro"
  port = 80
  region = "eu-central-1"

  min_cluster_size = 1
  max_cluster_size = 3
}


