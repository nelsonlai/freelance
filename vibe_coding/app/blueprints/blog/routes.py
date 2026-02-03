from flask import render_template, redirect, url_for, flash, request, abort
from flask_login import login_required, current_user
from app.blueprints.blog import blog_bp
from app.extensions import db
from app.models import Post


@blog_bp.route("/")
def index():
    page = request.args.get("page", 1, type=int)
    pagination = Post.query.order_by(Post.created_at.desc()).paginate(
        page=page, per_page=10
    )
    return render_template("blog/index.html", pagination=pagination)


@blog_bp.route("/<int:post_id>")
def view(post_id):
    post = Post.query.get_or_404(post_id)
    return render_template("blog/view.html", post=post)


@blog_bp.route("/create", methods=["GET", "POST"])
@login_required
def create():
    if request.method == "POST":
        title = request.form.get("title", "").strip()
        body = request.form.get("body", "").strip()
        if not title or not body:
            flash("Title and body are required.", "error")
            return render_template("blog/create.html")
        post = Post(title=title, body=body, author_id=current_user.id)
        db.session.add(post)
        db.session.commit()
        flash("Post created.", "success")
        return redirect(url_for("blog.view", post_id=post.id))
    return render_template("blog/create.html")


@blog_bp.route("/<int:post_id>/edit", methods=["GET", "POST"])
@login_required
def edit(post_id):
    post = Post.query.get_or_404(post_id)
    if post.author_id != current_user.id:
        abort(403)
    if request.method == "POST":
        title = request.form.get("title", "").strip()
        body = request.form.get("body", "").strip()
        if not title or not body:
            flash("Title and body are required.", "error")
            return render_template("blog/edit.html", post=post)
        post.title = title
        post.body = body
        db.session.commit()
        flash("Post updated.", "success")
        return redirect(url_for("blog.view", post_id=post.id))
    return render_template("blog/edit.html", post=post)


@blog_bp.route("/<int:post_id>/delete", methods=["POST"])
@login_required
def delete(post_id):
    post = Post.query.get_or_404(post_id)
    if post.author_id != current_user.id:
        abort(403)
    db.session.delete(post)
    db.session.commit()
    flash("Post deleted.", "info")
    return redirect(url_for("blog.index"))
