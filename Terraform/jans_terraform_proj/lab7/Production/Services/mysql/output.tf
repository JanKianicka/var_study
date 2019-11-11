output "password" {
  value = random.string.db_password.result
  description = "Database password"
  sensitive = true
}