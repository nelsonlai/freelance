from django.urls import path
from . import views

urlpatterns = [
    path("", views.survey, name="survey"),
    path("result/<int:pk>/", views.assessment_result, name="assessment_result"),
    path("blog/", views.post_list, name="blog"),

    # ✅ 新增：生成 AI 圖片
    path(
        "generate-ai/<int:assessment_id>/",
        views.generate_ai_images,
        name="generate_ai_images"
    ),
]