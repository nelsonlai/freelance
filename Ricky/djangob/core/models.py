from django.db import models


class Post(models.Model):
    title = models.CharField(max_length=100)
    content = models.TextField()
    created_at = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return self.title


# ✅ 新功能用嘅資料表
class Assessment(models.Model):
    weight = models.FloatField()
    height = models.FloatField()
    age = models.IntegerField()

    photo = models.ImageField(upload_to="photos/")

    # ✅ 新加：AI 生成後嘅圖片
    after_plan1 = models.ImageField(
        upload_to="generated/",
        null=True,
        blank=True
    )

    after_plan2 = models.ImageField(
        upload_to="generated/",
        null=True,
        blank=True
    )

    created_at = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return f"Assessment {self.id}"