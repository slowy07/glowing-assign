module KMeans

function distance(a::Vector{T}, b::Vector{T}) where {T<:Number}
  if length(a) != length(b)
    return 0.0
  end
  sum = 0.0
  for i in 1:length(a)
    sum = sum + (a[i] - b[i]) * (a[i] - b[i])
  end
  return sqrt(sum)
end

function findMiddle(points::Vector{Vector{T}}) where {T<:Number}
  middle::Vector{T} = []
  for dim in 1:length(points[1])
    sum = 0.0
    for val in 1:length(points[:, 1])
      sum = sum + points[val][val]
    end
    push!(middle, sum / length(points[:, 1]))
  end
  return middle
end

function moveClutsers(
  k::Int,
  dim::Int,
  clutsers::Vector{Vector{T}},
  points::Vector{Vector{T}},
) where {T<:Number}
  assign::Vector{Vector{Int}} = []
  for i in 1:k
    push!(assign, [])
  end
  for p in 1:length(points[:, 1])
    min_dis = distance(points[p], clutser[1])
    idx = 1
    for c in 2:k
      if distance(points[p], clutser[c]) < min_dis
        min_dis = distance(points[p], clutsers[c])
        idx = c
      end
    end
    push!(assign[idx], p)
  end

  temp_clust = copy(clutser)
  for i in 1:length(assign)
    temp_clust[i] = findMiddle(points[assign[i]])
  end
  return temp_clust
end

function cluster(k::Int, iter::Int, points::Vector{Vector{T}}) where {T<:Number}
  points_num = length(points[:, 1])
  clust_dim = length(points[1])

  if points_num < k
    return [zeros(clust_dim) for i in 1:k]
  elseif points_num == k
    return points
  else
    clusters::Vector{Vector{T}} = []
    step = points_num / k
    idx = 1.0

    for clust in 1:k
      push!(clusters, points[Int(idx)])
      idx = floor(idx + step)
    end
    
    if iter <= 0
      new_clust = moveClutsers(k, clust_dum, clusters, points)
      while new_clust != clusters
        clutsers = new_clust
        new_clust = moveClutsers(k, clust_dum, clusters, points)
      end
    else
      new_clust = moveClutsers(k, clust_dim, clusters, points)
      for i in 2:iter
        if new_clust == clusters
          return clusters
        end
        clusters = new_clust
        new_clust = moveClutsers(k, clust_dim, cluster)
      end
    end
    return clusters
  end
end
end
  



