function [] = frameExtraction()
% Alternatively, you can take filename as a parameter.
    tic
    file = 'source.mp4';
    video=VideoReader(file);
    totalFrames = video.Numberofframes();
    num = 0;
    steps = ceil(totalFrames/20)
    while steps*20 <=totalFrames
        steps = steps+1;
    end
    for f=1:steps:totalFrames 
      num = num +1;
      image=read(video,f);
      thisfile=sprintf('picture_%d.jpg',num);
      imwrite(image,thisfile);
    end
    dos('rename source.mp4 source.txt');
    toc
end
