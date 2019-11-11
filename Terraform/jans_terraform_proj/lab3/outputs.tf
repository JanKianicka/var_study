output "bucket_id" {
  # value = aws_instance.helloWorld.public_ip
  # I do not have functional creating aws_instance, let us try bucket
  value = aws_s3_bucket.main.id

}