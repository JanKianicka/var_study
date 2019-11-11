provider "aws" {
  region = "eu-central-1"
}

resource "aws_iam_user" "myusers" {
  # count = 4
  # using leghts of the array
  # count = lenght.(var.username)
  # name = var.username[count.index]
  # yet chaning to 'set'
  for_each = toset(var.username) # here we have each for value and each for key
  name = each.value

  tags = {
    purpose = "Jan terraform training course"
  }
}

resource "aws_iam_user" "jans_user" {
  name = "jans-user-s3"
  path = "/hq/devs"

  tags = {
    purpose = "tf_training"
  }
}

resource "aws_iam_user_policy" "full_s3" {
  name = "jans_plicy"
  user = aws_iam_user.jans_user.name
  # this did not work - JSON is copied from  https://console.aws.amazon.com/iam/home?region=eu-central-1#/policies$new?step=edit
  # from the wizard when new policy is being created and there is JSON tab.
  policy = <<EOF
  {
    "Version": "2012-10-17",
    "Statement": [
      {
        "Sid": "VisualEditor0",
        "Effect": "Allow",
        "Action": "s3:*",
        "Resource": "*"
      }
    ]
  }
  EOF
}

