from flask import Blueprint, jsonify, current_app
from ..services.storage import Storage
from ..utils.auth import require_admin

bp = Blueprint("admin_stats", __name__, url_prefix="/api/admin/stats")


def _store():
    return Storage(current_app.config["SQLITE_PATH"])


# =========================
# KPI summary
# =========================
@bp.get("/kpis")
@require_admin
def kpis():
    return jsonify(_store().kpis())


# =========================
# Group count (pie / bar)
# =========================
@bp.get("/cat-breed")
@require_admin
def cat_breed():
    return jsonify(_store().group_count("cat_breed"))


@bp.get("/cat-sex")
@require_admin
def cat_sex():
    return jsonify(_store().group_count("cat_sex_status"))


@bp.get("/cat-source")
@require_admin
def cat_source():
    return jsonify(_store().group_count("cat_source"))


@bp.get("/vet-frequency")
@require_admin
def vet_frequency():
    return jsonify(_store().group_count("vet_frequency"))


# =========================
# Yes / No health stats
# =========================
@bp.get("/yesno/health")
@require_admin
def health_yesno():
    store = _store()
    return jsonify({
        "digestive_issues": store.group_count("digestive_issues"),
        "chronic_disease": store.group_count("chronic_disease"),
        "genetic_disease_known": store.group_count("genetic_disease_known"),
    })


# =========================
# Histograms (統一轉成 Array)
# =========================
def _hist_to_array(hist: dict):
    """
    { labels: [...], counts: [...] }
    → [ {label, value}, ... ]
    """
    return [
        {"label": hist["labels"][i], "value": hist["counts"][i]}
        for i in range(len(hist["labels"]))
    ]


@bp.get("/hist/cat-age")
@require_admin
def hist_cat_age():
    hist = _store().histogram_int(
        "cat_age",
        bins=[0, 1, 3, 6, 10, 20]
    )
    return jsonify(_hist_to_array(hist))


@bp.get("/hist/owning-years")
@require_admin
def hist_owning_years():
    hist = _store().histogram_int(
        "owning_years",
        bins=[0, 1, 3, 5, 10, 20]
    )
    return jsonify(_hist_to_array(hist))


@bp.get("/hist/life-fulfillment")
@require_admin
def hist_life():
    hist = _store().histogram_int(
        "life_fulfillment",
        bins=[0, 4, 7, 9, 11]
    )
    return jsonify(_hist_to_array(hist))
