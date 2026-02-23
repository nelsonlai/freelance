import os
print("POE_API_KEY =", os.getenv("POE_API_KEY"))

from django.shortcuts import render, redirect, get_object_or_404
from .models import Post, Assessment

def post_list(request):
    posts = Post.objects.order_by('-created_at')
    return render(request, 'core/post_list.html', {'posts': posts})

def post_detail(request, pk):
    post = get_object_or_404(Post, pk=pk)
    return render(request, 'core/post_detail.html', {'post': post})

def survey(request):
    if request.method == "POST":
        weight = request.POST.get("weight")
        height = request.POST.get("height")
        age = request.POST.get("age")
        photo = request.FILES.get("photo")

        assessment = Assessment.objects.create(
            weight=weight,
            height=height,
            age=age,
            photo=photo,
        )

        # ✅ 成功後跳去第二頁
        return redirect("assessment_result", pk=assessment.id)

    return render(request, "core/survey.html")

def assessment_result(request, pk):
    assessment = get_object_or_404(Assessment, pk=pk)

    return render(request, "core/assessment_result.html", {
        "assessment": assessment
    })
# ✅ 新增：Generate AI Images
def generate_ai_images(request, assessment_id):
    assessment = get_object_or_404(Assessment, id=assessment_id)

    # ✅ 暫時用「假 AI」：直接複製原圖
    assessment.after_plan1 = assessment.photo
    assessment.after_plan2 = assessment.photo

    assessment.save()

    return redirect("assessment_result", pk=assessment.id)