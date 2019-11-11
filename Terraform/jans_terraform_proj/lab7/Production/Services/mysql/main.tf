module "example_mysql" {
  source = "../../../module/Services/mysql"
  username = "root"
  password = "root1234"
}

# for password we can use random string by terraform
# can be referecend by random.

resource "random_string" "db_password" {
  length = 24
  lower = true
}