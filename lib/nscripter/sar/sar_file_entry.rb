# SAR file entry
class SarFileEntry
  attr_reader :file_name
  attr_reader :data_origin
  attr_reader :data_size

  def initialize(file_data_origin)
    @data_offset = file_data_origin
  end

  def read!(file)
    @file_name = ''
    while (c = file.read(1)) != "\0"
      @file_name += c
    end

    @data_origin,
    @data_size = file.read(8).unpack('L>L>')
    self
  end

  def extract(input_file, target_path)
    input_file.seek(@data_offset + @data_origin, IO::SEEK_SET)
    data = input_file.read(@data_size)
    open(target_path, 'wb') { |output_file| output_file.write(data) }
  end
end
